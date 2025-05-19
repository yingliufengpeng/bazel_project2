
cpp_code = '''

#include <iostream>

namespace generated {{
    
    class {class_name} {{
    
    public:
    
        void sayHello() {{
            std::cout << "{message}" << std::endl;
        }}
        
        
        
    }};
    

}}

'''


def generate_cpp_code(output_path, tmplate_file, class_name, message):
    with open(tmplate_file) as f_cpp_template:
        cpp_code = f_cpp_template.read()
        with open(output_path, 'w') as f:
            f.write(cpp_code.format(class_name=class_name, message=message))


if __name__ == '__main__':
    import sys
    print(f'execute args are: {sys.argv}')
    if len(sys.argv) != 5:
        print("Usage: generate_cpp.py usage <output> <class_name>  <message> ")
        sys.exit(-1)

    _, output, tmplate_file, class_name, message = sys.argv

    generate_cpp_code(output,tmplate_file, class_name, message)