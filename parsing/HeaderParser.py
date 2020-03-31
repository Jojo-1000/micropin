
import sys
import os
import io
import argparse

import pcpp
from pcpp import OutputDirective, Action

class Register:
    width: int
    name: str
    addr: int
    def __repr__(self):
        return "%s(0x%02x)" % (self.name, self.addr)

pcpp.CmdPreprocessor
# Processes register definition file and only leaves defines for registers
class SFRPreprocessor(pcpp.Preprocessor):
    def __init__(self):
        super().__init__()
        self.bypass_ifpassthru = False
        self.potential_include_guard = None
        self.registers = []
        self.define("_AVR_IO_H_ 1")
        self.reg_macro_start = '_SFR_IO'
        self.line_directive = None
        
    def on_comment(self, tok):
        # Pass through comments
        return True

    def on_directive_handle(self, directive, toks, ifpassthru, precedingtoks):
        if ifpassthru:
            if directive.value == 'if' or directive.value == 'elif' or directive == 'else' or directive.value == 'endif':
                self.bypass_ifpassthru = len([tok for tok in toks if tok.value == '__PCPP_ALWAYS_FALSE__' or tok.value == '__PCPP_ALWAYS_TRUE__']) > 0
            if not self.bypass_ifpassthru and (directive.value == 'define' or directive.value == 'undef'):
                if toks[0].value != self.potential_include_guard:
                    raise OutputDirective(Action.IgnoreAndPassThrough)  # Don't execute anything with effects when inside an #if expr with undefined macro
        super().on_directive_handle(directive,toks,ifpassthru,precedingtoks)
        if directive.value == 'define':
            if self.is_register_define(toks):
                self.add_register(toks)
                return None
            # only leave register definitions for now, bits are too inconsistent
            #if self.could_be_port_define(toks) and self.current_register is not None:
            #    if toks[0].lineno == self.next_line:
            #        self.next_line += 1
            #        return None
        return None  # Pass through where possible

    def on_potential_include_guard(self,macro):
        self.potential_include_guard = macro
        return super().on_potential_include_guard(macro)

    def on_include_not_found(self,is_system_include,curdir,includepath):
        raise OutputDirective(Action.IgnoreAndPassThrough)

    def is_register_define(self, toks):
        return len(toks) >= 3 and toks[2].value.startswith(self.reg_macro_start)

    def add_register(self, toks):
        r = Register()
        r.name = toks[0].value;
        try:
            r.width = int(toks[2].value[len(self.reg_macro_start):])
            r.addr = int([tok for tok in toks if tok.type == self.t_INTEGER][0].value, base=0)
            self.registers.append(r)
        except:
            pass

    def could_be_port_define(self, toks):
        return len(toks) >= 3 and toks[2].type == self.t_INTEGER

parser = argparse.ArgumentParser(description="Parses avr io headers for register definitions.")
parser.add_argument('inputs', metavar='input', nargs='*', type=argparse.FileType(), help='File(s)to process')
parser.add_argument('--output-dir', dest='output_dir', default='output', metavar='path', help='Output directory for generated files')
parser.add_argument('--output-preprocessed', dest='output_preprocessed',action='store_true', 
                    help='Also output preprocessed header files containing only defines.\nCan be used to extract additional information.')
parser.add_argument('--input-dir', dest='input_dir', help='Process all header files in directory.')

args = parser.parse_args(sys.argv[1:])

input_files = args.inputs
output_dir = args.output_dir

extension = '.hpp'
include_guard_prefix = 'MICROPIN_DETAIL_'
include_guard_postfix = '_INCLUDED'
namespace = 'MicroPin'
required_includes = []

output_files = []

def output_registers(source_filename: str,filename: str, registers: [Register]):
    include_guard = include_guard_prefix + filename.rpartition('.')[0].upper() + include_guard_postfix
    output = open(output_dir + os.path.sep + filename, "wt")
    output.write("// Generated from " + source_filename + '\n')
    output.write('#ifndef ' + include_guard + '\n')
    output.write('#define ' + include_guard + '\n')
    for include in required_includes:
        output.write('#include "')
        output.write('"\n')
    output.write('namespace ' + namespace + '\n{\n')
    for r in registers:
        output.write('\tconstepxr Register')
        output.write(str(r.width))
        output.write(' r')
        output.write(r.name)
        output.write('{0x%02x};\n' % (r.addr))
    output.write('}\n\n#endif\n')
    output.close()

if not os.path.exists(output_dir):
    os.mkdir(output_dir)

if args.input_dir is not None:
    for file in os.listdir(args.input_dir):
        if file.endswith('.h'):
            input_files.append(open(args.input_dir + os.path.sep + file))

for input in input_files:
    preprocessor = SFRPreprocessor()
    filename = os.path.basename(input.name)
    preprocessor.parse(input)
    output_file = 'Reg' + filename.rpartition('.')[0].replace('io', '').capitalize() + extension
    if not args.output_preprocessed:
        # Discard preprocessed output
        tok = preprocessor.token()
        while tok is not None:
            tok = preprocessor.token()
        input.close()
    else:
        preprocessed_output = open(output_dir + os.path.sep + filename, 'wt')
        preprocessor.write(preprocessed_output)
        preprocessed_output.close()
        input.close()
    if len(preprocessor.registers) > 0:
        output_registers(filename, output_file, preprocessor.registers)
        output_files.append(output_file)
        print('Parsed %s -> %s' % (filename, output_file))
    else:
        print('Skipped %s because it contained no register definitions' % (file))