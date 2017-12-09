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
#ifndef LOGGER_H
#define LOGGER_H

#include "common.h"


struct log_opt
{
    bool console;  //if true the message will be printed in the console
    bool file;     //if true the message will be printed in the log file

    bool err_quit; //if true the application will quit when a fatal error occurs

    log_opt();
    log_opt(bool _err_quit, bool _console = true, bool _file = true);
};

enum log_type
{
    normal,
    warning,
    error
};

struct log_data
{
    log_opt opt;
    string msg;
    log_type type;

    log_data();
    log_data(log_opt, string, log_type);
};

struct msg
{
    msg(string in)
    {
        data = in;
    }
    string data;
};

struct warn
{
    warn(string in)
    {
       data = in;
    }
    string data;
};

struct err
{
    err(string in)
    {
        data = in;
    }
    string data;
};

class LoggerOStream
{
    public:
        virtual void operator << (const log_data&) = 0;
        virtual void flush() = 0;
};

class Logger_stdout : public LoggerOStream
{
    public:
        Logger_stdout() {}
        void operator << (const log_data&);
        void flush();
};

class Logger_file : public LoggerOStream
{
    private:
        ofstream ofile;
    public:
        Logger_file(string filename)  : ofile(filename){}

        void operator << (const log_data&);
        void flush();
};

class logger
{
    public:

        logger(string log_file_path);
        logger();
        virtual ~logger();

        void log_message(string msg, log_opt opt);  //Logs the argument as a normal state message
        void log_warning(string msg, log_opt opt);  //Logs the argument as a non fatal state message
        void   log_error(string msg, log_opt opt);  //Logs the argument as a fatal state message

        void operator << (msg in);
        void operator << (warn in);
        void operator << (err in);
        //string operator << (string in);

    protected:

    private:

        vector<LoggerOStream*> output_streams = {new Logger_stdout()};
        vector<log_data> log;       //just a vector containing all the log strings
};

#endif // LOGGER_H
