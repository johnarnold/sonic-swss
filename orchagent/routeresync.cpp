#include <stdlib.h>
#include <iostream>
#include <vector>
#include "common/dbconnector.h"
#include "common/producertable.h"

using namespace std;
using namespace swss;

void usage(char **argv)
{
    cout << "Usage: " << argv[0] << " [start|stop]" << endl;
}

int main(int argc, char **argv)
{
    DBConnector db(APPL_DB, "localhost", 6379, 0);
    ProducerTable r(&db, APP_ROUTE_TABLE_NAME);

    if (argc != 2)
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    std::string op = std::string(argv[1]);
    if (op == "stop")
    {
        r.del("resync");
    }
    else if (op == "start")
    {
        std::vector<FieldValueTuple> fvVector = {};
        r.set("resync", fvVector);
    }
    else
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
