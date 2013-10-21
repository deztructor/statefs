#ifndef _STATEFS_PRIVATE_CONFIG_HPP_
#define _STATEFS_PRIVATE_CONFIG_HPP_
/**
 * @file config.hpp
 * @brief Statefs configuration access, private header
 *
 * @author (C) 2012, 2013 Jolla Ltd. Denis Zalevskiy <denis.zalevskiy@jollamobile.com>
 * @copyright LGPL 2.1 http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
 */

#include <statefs/config.hpp>

#include <cor/inotify.hpp>
#include <cor/options.hpp>

//#include <thread>
#include <future>

#include <boost/filesystem.hpp>

#include <poll.h>

namespace statefs { namespace config {

class Monitor
{
public:

    typedef std::shared_ptr<config::Library> lib_ptr;
    typedef std::map<std::string, lib_ptr> config_map_type;

    Monitor(std::string const &, ConfigReceiver &);
    ~Monitor();

private:
    int watch_thread();
    bool process_poll();
    int watch();
    void lib_add(std::string const &cfg_path, lib_ptr p);
    void lib_rm(std::string const &name);

    cor::inotify::Handle inotify_;
    std::string path_;
    cor::FdHandle event_;
    ConfigReceiver &target_;

    std::unique_ptr<cor::inotify::Watch> watch_;
    std::array<pollfd, 2> fds_;
    std::thread mon_thread_;

    config_map_type files_libs_;
};

bool check_name_load(std::string const &, config_receiver_fn);

std::string dump(std::string const&, std::ostream &
                 , std::string const&, std::string const&);

void save(std::string const&, std::string const&, std::string const&);
void rm(std::string const &, std::string const &, std::string const&);

}} // namespaces

#endif // _STATEFS_PRIVATE_CONFIG_HPP_
