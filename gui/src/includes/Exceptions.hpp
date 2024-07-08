/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-robin.glaude
** File description:
** Exceptions.hpp
*/

#pragma once

#include <exception>
#include <stdexcept>
#include <string>

namespace zappy {
    class ZappyException : public std::exception {
        public:
            ZappyException(const std::string &message) : _message(message) {}
            ~ZappyException() = default;
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };
    class TCPException : public ZappyException {
        public:
            TCPException(const std::string &message) : ZappyException(message) {}
            ~TCPException() = default;
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };
    class TcpParserException : public ZappyException {
        public:
            TcpParserException(const std::string &message) : ZappyException(message) {}
            ~TcpParserException() = default;
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };
    class GUIException : public ZappyException {
        public:
            GUIException(const std::string &message) : ZappyException(message) {}
            ~GUIException() = default;
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };
}
