drop function if exists tu64_test();
--
CREATE FUNCTION tu64_test() RETURNS BOOLEAN
 AS 'pg_tu64.so', 'tu64_test'
 LANGUAGE C STRICT;
--
CREATE FUNCTION tu64_cmp() RETURNS BOOLEAN
 AS 'pg_tu64.so', 'tu64_cmp'
 LANGUAGE C STRICT;
