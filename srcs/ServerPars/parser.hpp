//
// Created by ballet on 24/05/17.
//

#ifndef PARSER_H_
# define PARSER_H_

class std::map;
class std::string;

namespace   Indie {
    class   Parser {
    private:
        using cmdPtr = void (Parser::*)(std::string);

    private:
        static const std::map<std::string, cmdPtr> fnc;

    public:
        Parser();
        ~Parser();

    private:
        void userConnect(std::string);
    };
}

#endif /* !PARSER_H_ */