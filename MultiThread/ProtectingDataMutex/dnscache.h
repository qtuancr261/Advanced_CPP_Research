/*
 * Author: tuantq3
 * File: dnscache.h
 *
 * Created on 27/4/2020
 */
#ifndef DNSCACHE_H
#define DNSCACHE_H
#include <boost/thread/shared_mutex.hpp>
#include <map>
#include <mutex>
#include <string>

class DNSCache {
public:
    using domain = std::string;
    using entry = std::string;

private:
    std::map<domain, entry> _entries;
    mutable boost::shared_mutex _entriesMutex;

public:
    DNSCache();
    entry findEntry(const domain& srcDomain) const;
    void updateEntry(const domain& srcDomain, const entry& entryUpdated);
};

#endif  // DNSCACHE_H
