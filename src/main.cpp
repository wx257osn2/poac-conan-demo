#include <cassert>
#include <leveldb/db.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

using namespace leveldb;

int main()
{
    spdlog::info("start test");

    DB* db = nullptr;
    Options options;
    options.create_if_missing = true;
    Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    if (!status.ok()) {
        spdlog::error("open db failed");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 8; ++i) {
        status = db->Put(WriteOptions{}, fmt::format("key-{}", i), fmt::format("value-{}", i));
        if (!status.ok()) {
            spdlog::error("put {} error: {}", i, status.ToString());
            continue;
        }

        spdlog::info("insert key {}", i);
    }
}
