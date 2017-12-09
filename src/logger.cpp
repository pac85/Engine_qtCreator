/**************************************************************************/
/*
  Copyright (C) 2017 Antonino Maniscalco (alias pac85)

  This file is part of Engine.

  Engine is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Engine is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Engine.  If not, see http://www.gnu.org/licenses/

*/
/**************************************************************************/
#include "logger.h"

//changes consoles's text color
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_YELLOW   = 33,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_YELLOW   = 43,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };

    Modifier red(FG_RED);
    Modifier green(FG_GREEN);
    Modifier yellow(FG_YELLOW);
    Modifier def(FG_DEFAULT);
}

void Logger_stdout::operator <<(const log_data& data)
{
    switch(data.type)
    {
        case normal:
            cout << "[  "   << Color::green << "OK" << Color::def << "  ]" << data.msg << endl;
            break;
        case warning:
            cout << "[ " << Color::yellow << "WARN" << Color::def << " ]" << data.msg << endl;
            break;
        case error:
            cout << "[ " << Color::red << "ERROR" << Color::def << "]" << data.msg << endl;
            break;
    }
}

void Logger_stdout::flush()
{
    cout.flush();
}

void Logger_file::operator <<(const log_data& data)
{
    switch(data.type)
    {
        case normal:
            ofile << "[  OK  ]" << data.msg << endl;
            break;
        case warning:
            ofile << "[ WARN ]" << data.msg << endl;
            break;
        case error:
            ofile << "[ ERROR]" << data.msg << endl;
            break;
    }
}

void Logger_file::flush()
{
    ofile.flush();
}

logger::logger(string log_file_path)
{
    remove(log_file_path.c_str());      //removes old log file
    output_streams.push_back(new Logger_file(log_file_path));
}

logger::logger()
{

}

logger::~logger()
{

}

log_opt::log_opt()
{

}

log_opt::log_opt(bool _err_quit, bool _console, bool _file)
{
    console = _console, file = _file, err_quit = _err_quit;
}

log_data::log_data(log_opt _opt, string _msg, log_type _type)
{
    opt = _opt, msg = _msg, type = _type;
}

void logger::log_message(string msg, log_opt opt)
{
    for(auto& i : output_streams)
        *i << log_data(opt, msg, normal);

    if(opt.err_quit)
    {
        for(auto& i : output_streams)
        i->flush();
        exit(-1);
    }
}

void logger::log_warning(string msg, log_opt opt)
{
    for(auto& i : output_streams)
        *i << log_data(opt, msg, warning);

    if(opt.err_quit)
    {
        for(auto& i : output_streams)
        i->flush();
        exit(-1);
    }
}

void   logger::log_error(string msg, log_opt opt)
{
    for(auto& i : output_streams)
        *i << log_data(opt, msg, error);

    if(opt.err_quit)
    {
        for(auto& i : output_streams)
        i->flush();
        exit(-1);
    }
}

void logger::operator << (msg in)
{
    log_message(in.data, log_opt(false, true));
}

void logger::operator << (warn in)
{
    log_warning(in.data, log_opt(false, true));
}

void logger::operator << (err in)
{
    log_error(in.data, log_opt(true, true));
}

/*string logger::operator << (string in)
{

}*/


