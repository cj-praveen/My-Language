import os, sys

class Interpreter:

    def __init__(self, code: str, debug: bool = False) -> None:
        
        self.code: list[str] = [*code]
        self.pos: int = 0
        self.chunk: str = ""
        self.debug: bool = debug
        self.run()


    def make_string(self) -> str | int:

        string: str = ""

        for i in self.code[self.pos:]:
            if i == "\"" and i != "\\\"":
                string += i
                break

            string += i
            self.pos += 1

        return string[:-1] if string[(len(string) - 1):] == "\"" else 1

    def make_tokens(self) -> list[any]:
    
        tokens: list[any] = []

        while self.pos < len(self.code):

            self.chunk += self.code[self.pos]

            if self.code[self.pos] == "\n":
                chunk = ""
            elif self.code[self.pos] == ";":
                chunk = ""
            elif self.code[self.pos] == "\"":
                self.pos += 1
                tokens.append(self.make_string())
                self.chunk = ""
                continue
            elif self.code[self.pos] == "#":
                break

            if self.chunk == "print":
                tokens.append(13)
                chunk = ""
            elif self.chunk == "exit":
                tokens.append(0)
                chunk = ""

            self.pos += 1

        return tokens

    def run(self) -> None:

        i: int = 0
        tokens: list[any] = self.make_tokens()

        print(len(tokens), tokens) if self.debug else ...

        while i < len(tokens):
            if tokens[i] == 13 and len(tokens) > 1:
                if isinstance(tokens[i+1], str):
                    print(tokens[i+1])
                    i += 1
                elif isinstance(tokens[i+1], int) and tokens[i+1] == 1:
                    print("Syntax Error")
                    i += 1
            elif tokens[i] == 0:
                exit(0)

            i += 1


if __name__ == "__main__":
    while True:
        code: str = str(input("~ "))
        try:
            Interpreter(code)
        except Exception as err:
            print("Python Error:", err)
            exit(1)

