/*
 * Author: tuantq3
 * File: dnscache.cpp
 *
 * Created on 27/4/2020
 */
#include "dnscache.h"

DNSCache::DNSCache() : _entries{} {}

DNSCache::entry DNSCache::findEntry(const DNSCache::domain &srcDomain) const {
    boost::shared_lock<boost::shared_mutex> rlock(_entriesMutex);
    auto iterFound = _entries.find(srcDomain);
    return (iterFound == _entries.end() ? " " : iterFound->second);
}

void DNSCache::updateEntry(const DNSCache::domain &srcDomain, const DNSCache::entry &entryUpdated) {
    std::lock_guard<boost::shared_mutex> wlock(_entriesMutex);
    _entries.at(srcDomain) = entryUpdated;
}
