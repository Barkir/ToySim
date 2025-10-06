# какие команды нужно парсить?
# J
# CBIT
# SUBI
# MOVN
# BEQ
# BEXT
# LDP
# ADD
# LD
# CLS
# RORI
# ST
# XOR
# SYSCALL








class Parser
    INSTRUCTION_SET = { # constant value written in CAPITAL LETTERS (this is a hash table)
        'J'    => 0b010111
        'CBIT' => 0b111011
        'SUBI' => 0b001111
        'MOVN' => 0b000101
        'BEQ'  => 0b100110
        'BEXT' => 0b110110
        'LDP'  => 0b001110
        'ADD'  => 0b000110
        'LD'   => 0b100010
        'CLS'  => 0b101101
        'RORI' => 0b111111
        'ST'   => 0b111010
        'XOR'  => 0b011011
        'SYSCALL' => 0b000111
    }.freeze # nobody can change me!
    def get_tokens(text)
        text.lines.map do |line|
            line = line.split(";", 2).first || line # fuck comments
            line = line.strip
            tokens = line.split.map {|t| t.delete(",")} # deleting commas (fuck commas)
        end.reject(&:empty?) # deleting empty elements
    end

    def
end



# -------- TESTING --------
if __FILE__ == $0
    parser = Parser.new
    source = File.read("file.txt")
    tokens = parser.get_tokens(source)
    pp tokens
end

