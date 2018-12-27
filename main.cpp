#include <iostream>
#include <thread>

//
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>


#include <picosha2.h>

#include <stdlib.h>

void Logging()
{
    
    typedef boost::log::sinks::synchronous_sink <boost::log::sinks::text_ostream_backend> text_sink;

    boost::shared_ptr< text_sink> sink = boost::make_shared< text_sink >();

    sink->locked_backend()->add_stream(boost::make_shared< std::ofstream >("sample.log")); //добаление потока для записи

    boost::log::core::get()->add_sink(sink);

    boost::log::core::get()->set_filter
    (boost::log::trivial::severity >= boost::log::trivial::trace ||  boost::log::trivial::severity >= boost::log::trivial::info);
}


void find (const int &m) {
    while (1) {
        //std::vector<char> array{(char) std::rand(), (char) std::rand() , (char) std::rand() , (char) std::rand() };
       // std::string str;
        str[0] = (char) std::rand();
        str[1] = (char) std::rand();
        str[2] = (char) std::rand();
        str[3] = (char) std::rand();
        str[5] = '\0';
        if (picosha2::hash256_hex_string(str).substr(31, 1) == "0") {
            BOOST_LOG_TRIVIAL(trace) << "hash with 0000" << picosha2::hash256_hex_string(str);
        } else {
            BOOST_LOG_TRIVIAL(info) << "thread = " << m << " " << "hash = " << picosha2::hash256_hex_string(str);
        }
    }
}



int main(int argc, char* argv[]) {

    std::srand(time(nullptr));

    auto M = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    std::cout<<M;

    std::cin >> M ;

//    if (argc == 2 ) {
//        M = atoi(argv[1]);
//    }
//    else {
//        if (argc > 2){
//            std::cout<< "error" << std::endl;
//        }
//    }

    for (unsigned int m = 0; m < M; ++m)
    {
        threads.emplace_back(find, m);
    }

    for (unsigned int m = 0; m < M; ++m)
    {
        threads[m].join();
    }

    return 0;
}
