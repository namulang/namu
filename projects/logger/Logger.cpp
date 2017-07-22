#include "Includes.hpp"
#include <vector>
#include <string>
#include <iostream>

namespace NE
{
    using namespace std;
    class Stream {
    public:
        Stream() : _is_enable(true) {}

        /// @return true means an error.
        virtual type_bool dump(const char* message) { return ! _is_enable; }
        type_bool isEnable() const { return _is_enable; }
        void setEnable(type_bool is_enable) { _is_enable = is_enable; }
        virtual const char* getName() const = 0;
        virtual type_bool initialize() { return false; }

    private:
        type_bool _is_enable;
    };
    class ConsoleStream : public Stream {
    public:
        virtual const char* getName() const { return "ConsoleStream"; }
        virtual type_bool dump(const char* message) {
            if(Stream::dump(message)) return true;

            std::cout << message << "\n";
            return false;
        }
    };

    namespace
    {
        template <typename T>
        T& nullreference() {
            T* nulled = 0;
            return *nulled;
        }
    }

    class Logger : public Stream
    {
    public:
        virtual const char* getName() const { return "Logger"; }
        const Stream& operator[](type_index n) const { return getStream(n); }
        Stream& operator[](type_index n) { return getStream(n); }
        const Stream& operator[](const char* message) const { return getStream(message); }
        Stream& operator[](const char* message) { return getStream(message); }

        Stream& getStream(type_index n) { 
            if(n < 0 || n >= getStreamCount())
                return nullreference<Stream>();

            return *_streams[n]; 
        }
        const Stream& getStream(type_index n) const {
            Logger* unconsted = const_cast<Logger*>(this);

            return unconsted->getStream(n);
        }
        const Stream& getStream(const char* c_message) const { 
            string message = c_message;
            for(auto e : _streams)
                if(string(e->getName()) == message)
                    return *e;

            return nullreference<Stream>();
        }
        Stream& getStream(const char* message) {
            const Logger* consted = this;

            return const_cast<Stream&>(consted->getStream(message));
        }
        type_count getStreamCount() const { return _streams.size(); }
        virtual type_bool dump(const char* message) {
            type_bool result = false;
            for(auto e : _streams)
                result |= e->dump(message);
            
            return result;
        }
        type_bool pushStream(Stream* new_stream) {
            if( ! new_stream) return true;

            _streams.push_back(new_stream);
            return false;
        }
        virtual type_bool initialize() {
            type_bool result = false;
            for(auto e : _streams)
                result |= e->initialize();

            return result;
        }
        static Logger& getInstance() {
            static Logger inner;
            return inner;
        }

    private:
        Logger() : Stream() {}
        Logger(const Logger& rhs) : Stream(rhs) {}        

    private:
        std::vector<Stream*> _streams;
    };
}