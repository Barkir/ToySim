# TOY ISA (interpreter)
![alt text](readme/image.png)

#### HOW TO USE (clone (🤡) these commands)

```
git clone https://github.com/Barkir/ToySim
```
```
cd ToySim
```

_make sure you're in root dir of this repo_

```
chmod +x ./get_ready.sh
./get_ready.sh
```

### ⚠️⚠️⚠️ WARNING
- Before writing the code on microassembler - **plz** install only 1 variable. Here's the instruction.
1. `cd build`
2. `pwd` and copy it
3. Go to constants.rb
4. Find `TOY_SIM` constant and clear it
5. Insert the path of `ToySim` that you copied



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

| Command | Notes     | made it (both in asm and interpreter) |
|---------|-----------|---------|
| movn rd, rs, rt    | if (rt) then rd = rs                 | ☑️        |
| add rd, rs, rt     | rd = rs + rt                         | ☑️        |
| subi rt, rs, imm   | rd = rs - imm                        | ☑️        |
| jmp t    | pc = pc + t                                    | ☑️        |
| cbit    |                                                 | ☑️        |
| beq rs, rt, offset     | if (rs == rt) pc = pc + offset   | ☑️        |
| bext    |                                                 | ☑️        |
| ldp     |                                                 | ☑️        |
| ld      |                                                 |         |
| cls     |                                                 |         |
| rori    |                                                 |         |
| st      |                                                 |         |
| xor     |                                                 | ☑️        |
| syscall | r8 - system call number, r0-r7 - args, r0-result| ☑️        |

#### Ruby features
1. A class has default methods.
    - `initialize` - a method which initializes some sh...
    - `method_missing` - handles the situation when some method is missed in a class


**This is a usecase for `method_missing`**

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

## Interpreter
