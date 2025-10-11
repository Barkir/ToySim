# TOY ISA (interpreter)
![alt text](image-1.png)


## MicroAssembler
I use [ruby](https://www.ruby-lang.org/en/) for writing microassembler.

On the first commits you can see that I used it kinda differently (as a parser, not as a microassembler).

The clue is we don't need to write a parser itself, because Ruby's syntax allows us to call class methods in the way we call assembler instructions

For example, the function can be called in two ways

```ruby
movn(r1, r31, 42)
```

```ruby
movn r1, r31, 42
```

Those are equal! So `movn` is just a method of the class called `MicroAsm` which you can look at [here](./toy_isa.rb)

#### Commands

| Command | Notes     |
|---------|-----------|
| movn    |           |
| add     |           |
| subi    |           |
| jmp     |           |
| cbit    |           |
| beq     |           |
| bext    |           |
| ldp     |           |
| ld      |           |
| cls     |           |
| rori    |           |
| st      |           |
| xor     |           |
| syscall | r8 - system call number, r0-r7 - args, r0-result            |

#### Ruby features
1. A class has default methods.
    - `initialize` - a method which initializes some sh...
    - `method_missing` - handles the situation when some method is missed in a class

This is a usecase for `method_missing`

I got `st` instruction in microassembler

Its' syntax - `st rt, offset(base)`

`offset` is a number and `base` is a base register.

so, we call it like this `st r1, 42(r2)`

In Ruby we can call it like this `st r1, 42.r2`

HOOOOOOW?

`42` is an object of `Integer` class. And then we call a method of it called `r2`. But we don't have such method by default, so we can define it with `method_missing` method.

Here's how I made it.

```ruby
class Integer
    def method_missing(name, *args)
        if name.to_s =~ /^r([1-9]|[12][0-9]|[3][01])$/ && args.empty?
            return {offset: self, base: name}
        end
    end
end
```

`/^r([1-9]|[12][0-9]|[3][01])$/` looks frightening.

It means that if our method starts from `r` and it has

```
numbers from 1 to 9

or

numbers 1,2 as the first one and 0-9 as the second one

or

number 3 as the first one and 0,1 as the second one
```


It mathes our case and we return a dictionary where we contain our object and the **name** of this _fictional_ method as a string.
