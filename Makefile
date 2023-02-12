# pg_tu64 Makefile

MODULES = pg_tu64

EXTENSION = pg_tu64
DATA = pg_tu64--0.0.1.sql
PGFILEDESC = "pg_tu64 - test uint64_t"


#REGRESS_OPTS = --temp-instance=/tmp/5454 --port=5454 --temp-config pg_query_rewrite.conf
#REGRESS=test0 test1 test2 test3 test4 test5 test6 test7

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

#
