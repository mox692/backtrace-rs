### GDBでデバッグする


```
cargo build --example mac

lldb ./target/debug/examples/mac

RUSTFLAGS="-C link-arg=-Wl,-keep_dwarf_unwind -C link-arg=-Wl,-no_compact_unwind" cargo run --example mac
```

```
// 通常実行
cargo run --example mac
```

## memo
my_function: 0x0000000100001550
