use backtrace::Backtrace;

fn main() {
    println!("{:?}", Backtrace::new());
    println!("-----------------------");

    // backtrace::trace(|frame| {
    //     let below_root = !ptr::eq(frame.symbol_address(), active_frame.inner_addr);

    //     // only capture frames above `Trace::leaf` and below
    //     // `Trace::root`.
    //     if above_leaf && below_root {
    //         frames.push(frame.to_owned().into());
    //         println!("frames pushed!!: {:?}", &frames);
    //     }

    //     if ptr::eq(frame.symbol_address(), trace_leaf as *const _) {
    //         above_leaf = true;
    //     }

    //     // only continue unwinding if we're below `Trace::root`
    //     below_root
    // });
    check_trace();
}

fn check_trace() {
    backtrace::trace(|frame| {
        let ip = frame.ip();
        let symbol_address = frame.symbol_address();

        // Resolve this instruction pointer to a symbol name
        backtrace::resolve_frame(frame, |symbol| {
            if let Some(name) = symbol.name() {
                if let Some(filename) = symbol.filename() {
                    if let Some(addr) = symbol.addr() {
                        println!(
                            "frame.symbol_address(): {:?}, addr: {:?}, name: {:?}, filename: {:?}",
                            frame.symbol_address(),
                            addr,
                            name,
                            filename
                        )
                        // ...
                    }
                    // ...
                }
                // ...
            }
        });
        true // keep going to the next frame
    });
}
