
#include <functional>
#include <memory>
#include <iostream>
#include <optional>
#include <type_traits>
#include <utility>

#include "main_extend.h"
#include "utils.h"
#include "Buffer.h"
#if defined(__GNUC__) || defined(__ICL) || defined(__clang__)
#define C10_LIKELY(expr) (__builtin_expect(static_cast<bool>(expr), 1))
#define C10_UNLIKELY(expr) (__builtin_expect(static_cast<bool>(expr), 0))
#else
#define C10_LIKELY(expr) (expr)
#define C10_UNLIKELY(expr) (expr)
#endif

#define TORCH_INTERNAL_ASSERT_DEBUG_ONLY(...) \
C10_EXPAND_MSVC_WORKAROUND(TORCH_INTERNAL_ASSERT(__VA_ARGS__))



/// MaybeOwnedTraits<T> describes how to borrow from T.  Here is how we
/// can implement borrowing from an arbitrary type T using a raw
/// pointer to const:
template <typename T>
struct MaybeOwnedTraitsGenericImpl {
  using owned_type = T;
  using borrow_type = const T*;

  static borrow_type createBorrow(const owned_type& from) {
    return &from;
  }

  static void assignBorrow(borrow_type& lhs, borrow_type rhs) {
    lhs = rhs;
  }

  static void destroyBorrow(borrow_type& /*toDestroy*/) {}

  static const owned_type& referenceFromBorrow(const borrow_type& borrow) {
    return *borrow;
  }

  static const owned_type* pointerFromBorrow(const borrow_type& borrow) {
    return borrow;
  }

  static bool debugBorrowIsValid(const borrow_type& borrow) {
    return borrow != nullptr;
  }
};

/// It is possible to eliminate the extra layer of indirection for
/// borrows for some types that we control. For examples, see
/// intrusive_ptr.h and TensorBody.h.

template <typename T>
struct MaybeOwnedTraits  ;

// Explicitly enable MaybeOwned<shared_ptr<T>>, rather than allowing
// MaybeOwned to be used for any type right away.
template <typename T>
struct MaybeOwnedTraits<std::shared_ptr<T>>
    : public MaybeOwnedTraitsGenericImpl<std::shared_ptr<T>> {};

/// A smart pointer around either a borrowed or owned T. When
/// constructed with borrowed(), the caller MUST ensure that the
/// borrowed-from argument outlives this MaybeOwned<T>. Compare to
/// Rust's std::borrow::Cow
/// (https://doc.rust-lang.org/std/borrow/enum.Cow.html), but note
/// that it is probably not suitable for general use because C++ has
/// no borrow checking. Included here to support
/// Tensor::expect_contiguous.
template <typename T>
class MaybeOwned final {
  using borrow_type = typename MaybeOwnedTraits<T>::borrow_type;
  using owned_type = typename MaybeOwnedTraits<T>::owned_type;

  bool isBorrowed_;
  union {
    borrow_type borrow_;
    owned_type own_;
  };

  /// Don't use this; use borrowed() instead.
  explicit MaybeOwned(const owned_type& t)
      : isBorrowed_(true), borrow_(MaybeOwnedTraits<T>::createBorrow(t)) {}

  /// Don't use this; use owned() instead.
  explicit MaybeOwned(T&& t) noexcept(std::is_nothrow_move_constructible_v<T>)
      : isBorrowed_(false), own_(std::move(t)) {}

  /// Don't use this; use owned() instead.
  template <class... Args>
  explicit MaybeOwned(std::in_place_t, Args&&... args)
      : isBorrowed_(false), own_(std::forward<Args>(args)...) {}

 public:
  explicit MaybeOwned() : isBorrowed_(true), borrow_() {}

  // Copying a borrow yields another borrow of the original, as with a
  // T*. Copying an owned T yields another owned T for safety: no
  // chains of borrowing by default! (Note you could get that behavior
  // with MaybeOwned<T>::borrowed(*rhs) if you wanted it.)
  MaybeOwned(const MaybeOwned& rhs) : isBorrowed_(rhs.isBorrowed_) {
    if (C10_LIKELY(rhs.isBorrowed_)) {
      MaybeOwnedTraits<T>::assignBorrow(borrow_, rhs.borrow_);
    } else {
      new (&own_) T(rhs.own_);
    }
  }

  MaybeOwned& operator=(const MaybeOwned& rhs) {
    if (this == &rhs) {
      return *this;
    }
    if (C10_UNLIKELY(!isBorrowed_)) {
      if (rhs.isBorrowed_) {
        own_.~T();
        MaybeOwnedTraits<T>::assignBorrow(borrow_, rhs.borrow_);
        isBorrowed_ = true;
      } else {
        own_ = rhs.own_;
      }
    } else {
      if (C10_LIKELY(rhs.isBorrowed_)) {
        MaybeOwnedTraits<T>::assignBorrow(borrow_, rhs.borrow_);
      } else {
        MaybeOwnedTraits<T>::destroyBorrow(borrow_);
        new (&own_) T(rhs.own_);
        isBorrowed_ = false;
      }
    }
    static_assert(isBorrowed_ == rhs.isBorrowed_);
    return *this;
  }

  MaybeOwned(MaybeOwned&& rhs) noexcept(
      // NOLINTNEXTLINE(*-noexcept-move-*)
      std::is_nothrow_move_constructible_v<T> &&
      std::is_nothrow_move_assignable_v<borrow_type>)
      : isBorrowed_(rhs.isBorrowed_) {
    if (C10_LIKELY(rhs.isBorrowed_)) {
      MaybeOwnedTraits<T>::assignBorrow(borrow_, rhs.borrow_);
    } else {
      new (&own_) T(std::move(rhs.own_));
    }
  }

  MaybeOwned& operator=(MaybeOwned&& rhs) noexcept(
      std::is_nothrow_move_assignable_v<T> &&
      std::is_nothrow_move_assignable_v<borrow_type> &&
      std::is_nothrow_move_constructible_v<T> &&
      // NOLINTNEXTLINE(*-noexcept-move-*)
      std::is_nothrow_destructible_v<T> &&
      std::is_nothrow_destructible_v<borrow_type>) {
    if (this == &rhs) {
      return *this;
    }
    if (C10_UNLIKELY(!isBorrowed_)) {
      if (rhs.isBorrowed_) {
        own_.~T();
        MaybeOwnedTraits<T>::assignBorrow(borrow_, rhs.borrow_);
        isBorrowed_ = true;
      } else {
        own_ = std::move(rhs.own_);
      }
    } else {
      if (C10_LIKELY(rhs.isBorrowed_)) {
        MaybeOwnedTraits<T>::assignBorrow(borrow_, rhs.borrow_);
      } else {
        MaybeOwnedTraits<T>::destroyBorrow(borrow_);
        new (&own_) T(std::move(rhs.own_));
        isBorrowed_ = false;
      }
    }
    return *this;
  }

  static MaybeOwned borrowed(const T& t) {
    return MaybeOwned(t);
  }

  static MaybeOwned owned(T&& t) noexcept(
      std::is_nothrow_move_constructible_v<T>) {
    return MaybeOwned(std::move(t));
  }

  template <class... Args>
  static MaybeOwned owned(std::in_place_t, Args&&... args) {
    return MaybeOwned(std::in_place, std::forward<Args>(args)...);
  }

  ~MaybeOwned() noexcept(
      // NOLINTNEXTLINE(*-noexcept-destructor)
      std::is_nothrow_destructible_v<T> &&
      std::is_nothrow_destructible_v<borrow_type>) {
    if (C10_UNLIKELY(!isBorrowed_)) {
      own_.~T();
    } else {
      MaybeOwnedTraits<T>::destroyBorrow(borrow_);
    }
  }

  // This is an implementation detail!  You should know what you're doing
  // if you are testing this.  If you just want to guarantee ownership move
  // this into a T
  bool unsafeIsBorrowed() const {
    return isBorrowed_;
  }

  const T& operator*() const& {
    if (isBorrowed_) {
      static_assert(
          MaybeOwnedTraits<T>::debugBorrowIsValid(borrow_));
    }
    return C10_LIKELY(isBorrowed_)
        ? MaybeOwnedTraits<T>::referenceFromBorrow(borrow_)
        : own_;
  }

  const T* operator->() const {
    if (isBorrowed_) {
      static_assert(
          MaybeOwnedTraits<T>::debugBorrowIsValid(borrow_));
    }
    return C10_LIKELY(isBorrowed_)
        ? MaybeOwnedTraits<T>::pointerFromBorrow(borrow_)
        : &own_;
  }

  // If borrowed, copy the underlying T. If owned, move from
  // it. borrowed/owned state remains the same, and either we
  // reference the same borrow as before or we are an owned moved-from
  // T.
  T operator*() && {
    if (isBorrowed_) {
      static_assert(
          MaybeOwnedTraits<T>::debugBorrowIsValid(borrow_));
      return MaybeOwnedTraits<T>::referenceFromBorrow(borrow_);
    } else {
      return std::move(own_);
    }
  }
};




struct Mn {

};

template <>
struct MaybeOwnedTraits<Mn> : public MaybeOwnedTraitsGenericImpl<Mn>   {};

template <typename T>
struct O {

};

struct Foo {
  int i;
  int j;
  Foo() {
    i = 1;
    j = 2;
    std::cout << "执行构造函数..." << i << j << std::endl;
  }

  ~Foo() {

    std::cout << "执行析构函数..." << i << j << std::endl;
  }
};

struct B;
struct A {
  std::shared_ptr<B> b;
  ~A() {
    std::cout << "b's count" << b.use_count() << std::endl;
    std::cout << "~A" << std::endl;
  }
};
struct B {
  std::weak_ptr<A> a;

  ~B() {
    std::cout << "a's count" << a.use_count() << std::endl;
    std::cout << "~B" << std::endl;
  }
};


struct BB;
struct AA {
  std::shared_ptr<BB> bb;
  ~AA() {
    std::cout << "~AA" << std::endl;
  }
};
struct BB {
  std::shared_ptr<AA> aa;

  ~BB() {
    std::cout << "~BB" << std::endl;
  }
};

struct P {
  int i ;
  operator bool() const noexcept {
    return i != 0;
  }
};

struct P2 {

  int i;
  int j;
  union {
    int* ptr;
    int arr[10];
  };

  operator bool() const noexcept {
    return i != j;
  }
};


struct Flags {
  bool a : 1;
  bool b : 1;
  bool c : 1;
  bool d : 1;
  bool e : 1;
};
// 重载 <<
std::ostream& operator<<(std::ostream& os, const Flags& f) {
  os << "Flags(a=" << f.a
     << ", b=" << f.b
     << ", c=" << f.c
     << ", d=" << f.d << ")";
  return os;
}

void process(const std::string& s) {
  std::cout << "左值引用版本\n";
}
void process(std::string&& s) {
  std::cout << "右值引用版本\n";
}

template<typename T>
void relay(T&& arg) {
  // 直接传递 arg
  process(std::forward<T>(arg));

}


template<typename F, typename... Args>
void log_and_call(F&& func, Args&&... args) {
  std::cout << "[LOG] calling function...\n";
  std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
}


auto f2(int a, int b) -> int {
  return a + b;
}

template<typename T>
auto fn3(T&& t) -> T {
  return std::forward<T>(t);
}

struct F4 {};

auto f4(F4&& o) {
  std::cout << "f4" << std::endl;
}
template <class T>
using SmallVectorSizeType =
    std::conditional_t<sizeof(T) < 4 && sizeof(void*) >= 8, uint64_t, uint32_t>;

using i_t = SmallVectorSizeType<uint32_t>;

auto div2(int a, int b) -> std::optional<float> {
  if (b == 0)
    return std::nullopt;
  return static_cast<float>(a) / b;
}

template <typename T>
auto div3(T& a, T& b) -> std::optional<T> {
  return a / b;
}

template <typename T>
auto div3(T&& a, T&& b) -> std::optional<T> {
  return div3(a, b);
}

template <typename T>
auto div4(T& a) -> std::optional<T> {
  return a;
}

template <typename T>
auto div4(T&& a) -> std::optional<T> {
  return a;
}


int main() {

  auto o1 = O<O<O<int8_t>>>();
  std::cout << &o1 << std::endl;

  auto mn1 = std::make_unique<Mn>(Mn());
  auto mn2 = std::make_shared<Mn>(Mn());
  auto mn3 = Mn();
  auto r1 = MaybeOwned<Mn>::borrowed(mn3);
  auto r2 = MaybeOwned<Mn>::owned(Mn());
  auto r3 = MaybeOwned<std::shared_ptr<Mn>>::borrowed(mn2);

  auto r4 = std::make_unique<Mn>(Mn());
  std::cout << "r4'count is " << r4.get() << std::endl;

  auto r5 = std::make_shared<Mn>(Mn());
  auto r6 = r5;
  auto r7 = r6;
  r6 = nullptr;
  std::cout << "r5'count is " << r5.use_count() << std::endl;

  char buffer[1024] = {0};
  Foo* f = new (buffer) Foo();  // placement new
  f->~Foo();                    // 手动析构

  auto b = std::make_shared<B>();
  auto a = std::make_shared<A>();
  (*a).b = b;
  (*b).a = a;

  {
    auto m = b;
    std::shared_ptr<B> *m2 = &b;
    std::cout << "b's count " << b.use_count() << std::endl;
  }
  std::cout << "b's count " << b.use_count() << std::endl;

  auto bb = std::make_shared<BB>();
  auto aa = std::make_shared<AA>();
  (*aa).bb = bb;
  (*bb).aa = aa;

  std::cout << "构造循环引用案例" << std::endl;

  auto p = P();
  std::cout << static_cast<bool>(p) << std::endl;
  p.i = 3;
  std::cout << p << std::endl;

  auto p2 = P2();
  std::cout << p2 << std::endl;

  p2.arr[1] = 355;
  // std::cout << p2.arr[1] << std::endl;
  //
  // std::cout << "ooo " << *(p2.ptr + 1) << std::endl;

  auto flags = Flags();
  flags.a = true;
  flags.b = false;

  std::cout << "flags is " << flags << std::endl;
  std::string s = "hi";
  relay(s);          // 左值
  relay(std::string("yo")); // 右值

  auto log_f = [](int a, int b) -> void {
    auto c = f2(a, b);
    std::cout << "a is " << a << " b is " << b << " c is " << c << std::endl;
  };

  log_and_call(log_f, 4, 45);

  auto r44 = fn3(44);
  std::cout << "r44 is " << r44 << std::endl;

  auto s_f4 = F4();
  f4(std::forward<F4>(s_f4));
  f4(F4());

  const i_t a8 = 3;
  std::cout << "a8 is " << typeid(a8).name() << std::endl;

  std::cout << sizeof(i_t) << std::endl;
  std::cout << sizeof(char) << std::endl;
  std::cout << sizeof(void*) << std::endl;


  auto r51 = div2(1, 2);
  std::cout << "r51 is " << *r51 << std::endl;
  auto r52 = div2(1, 0);

  if (r52.has_value()) {
    std::cout << "r52 is " << *r52 << std::endl;
  }

  auto r66 = 34;
  auto r61 = div3(std::move(r66), 2);
  std::cout << "r61 is " << *r61 << std::endl;
  auto r64 = div3(r66, r66);

  std::cout << "r61 is " << *r64 << std::endl;

  auto r67 = 34;
  auto r62 = div4(34);
  auto r63 = div4(r67);
  std::cout << "r62 is " << *r62 << std::endl;
  std::cout << "r63 is " << *r63 << std::endl;

  std::function<int()> m = []() -> int { return 3; };

  auto r71 = m();
  std::cout << "r71 is " << r71 << std::endl;

  std::cout << "--------------" << std::endl;
  ff1();

  std::cout << "vvvv ----"  << std::endl;
  std::vector<int> v1(3, 4);
  std::cout << "v1.size = " << v1.size() << std::endl; // 3

  auto v2 = std::move(v1);

  std::cout << "v2.size = " << v2.size() << std::endl; // 3
  std::cout << "v1.size = " << v1.size() << std::endl; // 0（正确行为）

  std::cout << "buffer test ..." << std::endl;
  auto bf1 = peng::Buffer(4);
  std::cout << "bf1.size() = " << bf1.size() << std::endl;

  auto bf2 = std::move(bf1);
  std::cout << "bf2.size() = " << bf2.size() << std::endl;
  std::cout << "bf1.size() = " << bf1.size() << std::endl;

#ifdef DEBUG_MODE
  std::cout << "DEBUG_MODE" << std::endl;
#endif

#ifdef USE_P_MATH
  auto add_r = add(3, 4);;
  std::cout << "add_r is " << add_r << std::endl;
#endif


  std::cout << "Compiler: ";

#if defined(__clang__)
  std::cout << "Clang " << __clang_major__ << "." << __clang_minor__ << std::endl;
#elif defined(__GNUC__)
  std::cout << "GCC " << __GNUC__ << "." << __GNUC_MINOR__ << std::endl;
#elif defined(_MSC_VER)
  std::cout << "MSVC (version " << _MSC_VER << ")" << std::endl;
#elif defined(__INTEL_COMPILER)
  std::cout << "Intel C++ (version " << __INTEL_COMPILER << ")" << std::endl;
#else
  std::cout << "Unknown compiler" << std::endl;
#endif

  std::cout << "Platform: ";
#if defined(_WIN32)
  std::cout << "Windows" << std::endl;
#elif defined(__linux__)
  std::cout << "Linux" << std::endl;
#elif defined(__APPLE__)
  std::cout << "macOS" << std::endl;
#else
  std::cout << "Unknown OS" << std::endl;
#endif


  P_ASSERT(3 == 3, "3 != 3");

  LOG("Hello");                    // ✅ 展开为 printf("[LOG] Hello\n");
  LOG("Sum: %d", 3 + 4);           // ✅ 展开为 printf("[LOG] Sum: %d\n", a + b);
  SAY_HELLO_WORLD();
  PRINT_DOUBLE(3);

  func_foo();
  func_bar();

  LOG_INFO("System started");
  LOG_WARN("Low memory");
  LOG_ERROR("Something went wrong");
  LOG_INFO("System finished!");
  LOG_ERROR("Failed at %s:%d", __FILE__, __LINE__);

  PRINT_DOUBLE(4);

  std::cout << GET_VAR(1) << std::endl;  // ✅ 输出 100
  std::cout << GET_VAR(2) << std::endl;  // ✅ 输出 200

  std::cout << TO_STRING(VALUE) << std::endl;  // ✅ 输出 "42"

  MAKE_VAR(foo) = 1;  // foo0
  MAKE_VAR(foo) = 2;  // foo1
  MAKE_VAR(foo) = 3;  // foo2

  TRY
    std::cout << "func is running ..." << std::endl;
    throw std::runtime_error("Division by zero!");
  CATCH



  return 0;
}