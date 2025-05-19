
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
    print(f'xxxxx {sys.argv}')
    if len(sys.argv) != 4:
        print("Usage: generate_cpp.py usage <output> <class_name>  <message> ")
        sys.exit(-1)

    _, output, class_name, message = sys.argv

    print(f'----------------- {output} -----')


    generate_cpp_code(output, class_name, message)