use backtrace::{self, Backtrace};
use std::{ffi::c_void, hint::black_box, ptr};

fn main() {
    // let s = Backtrace::new();
    black_box(my_function());
    end()
    // bar();
}

fn end() {}
fn foo() {
    bar()
}

fn bar() {
    let s = Backtrace::new();
    println!("-------------------------");
    // println!(
    //     "{:?}",
    //     s.frames()
    //         .iter()
    //         .map(|f| f.symbol_address())
    //         .collect::<Vec<_>>()
    // );
    println!("{:?}", s);
    println!("-------------------------");
}

fn break_point() {}

#[inline(never)]
fn my_function() {
    let function = my_function as *const c_void;
    println!("searching for symbol_address={:?}", function);

    // let s = Backtrace::new();
    // println!("{:?}", s);
    // println!("-------------------------");

    backtrace::trace(|frame| {
        // ここでresolveを図るべき
        backtrace::resolve_frame(frame, |symbol| {
            let s = symbol.addr().unwrap_or(&() as *const () as *mut c_void);
            let f = symbol.filename();
            let l = symbol.lineno();
            println!(
                "resolved void_ptr: {:p}, filename: {:?}, lineno: {:?}",
                s, &f, &l
            );
            break_point();
            // println!("symbol: {:?}", symbol.name());
        });

        if ptr::eq(frame.symbol_address(), function) {
            println!("found it!"); // not reached on aarch64-apple-darwin :(
            return false;
        }

        true
    });
}
