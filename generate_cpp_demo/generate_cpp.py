
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


def generate_cpp_code(output_path, class_name, message):
    with open(output_path, 'w') as f:
        f.write(cpp_code.format(class_name=class_name, message=message))


if __name__ == '__main__':
    import sys
    if len(sys.argv) != 4:
        print("Usage: generate_cpp.py usage <output> <class_name>  <message> ")

    _, output, class_name, message = sys.argv

    generate_cpp_code(output, class_name, message)