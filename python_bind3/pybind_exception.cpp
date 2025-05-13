#include <pybind11/pybind11.h>
#include <stdexcept>
#include <string>

namespace py = pybind11;

// 自定义 C++ 异常
class MyCustomException : public std::exception {
public:
    MyCustomException(const std::string &msg) : msg_(msg) {
    }

    const char *what() const noexcept override { return msg_.c_str(); }

private:
    std::string msg_;
};

// C++ 函数抛出异常
void risky_function() {
    throw MyCustomException("Something went wrong!");
}

PYBIND11_CONSTINIT static py::gil_safe_call_once_and_store<py::object> exc_storage;

void InitCustomException(py::module &m) {
    // 注册全局异常
    // py::register_exception<MyCustomException>(m, "MyCustomError");

    // 绑定函数
    m.def("risky_function", &risky_function);


    exc_storage.call_once_and_store_result(
        [&]() { return py::exception<MyCustomException>(m, "MyCustomError"); });
    py::register_exception_translator([](std::exception_ptr p) {
        try {
            if (p) std::rethrow_exception(p);
        } catch (const MyCustomException &e) {
            auto s = std::string(e.what());
            s += " !!!";
            py::set_error(exc_storage.get_stored(), s.data());
        } catch (const std::exception &e) {
            py::set_error(PyExc_RuntimeError, e.what());
        } catch (...) {
            py::set_error(PyExc_RuntimeError, "Unknown C++ exception");
        }
    });
}
