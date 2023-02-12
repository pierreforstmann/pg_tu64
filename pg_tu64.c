/*-------------------------------------------------------------------------
 *  
 *  pg_tu64
 * 
 * This program is open source, licensed under the PostgreSQL license.
 * For license terms, see the LICENSE file.
 *          
 * Copyright (c)  2023 Pierre Forstmann.
 *            
 *-------------------------------------------------------------------------
 */
#include "postgres.h"
#include "utils/guc.h"
#include "utils/snapmgr.h"
#include "utils/memutils.h"
#if PG_VERSION_NUM <= 90600
#include "storage/lwlock.h"
#endif
#include "pgstat.h"
#include "storage/ipc.h"
#include "storage/spin.h"
#include "miscadmin.h"
#if PG_VERSION_NUM >= 90600
#include "nodes/extensible.h"
#endif
#if PG_VERSION_NUM > 120000
#include "nodes/pathnodes.h"
#endif
#include "nodes/plannodes.h"
#include "utils/datum.h"
#include "utils/builtins.h"
#include "unistd.h"
#include "funcapi.h"
#include "catalog/pg_type.h"
#include "commands/dbcommands.h"

PG_MODULE_MAGIC;

/*---- Function declarations ----*/

void		_PG_init(void);
void		_PG_fini(void);

PG_FUNCTION_INFO_V1(tu64_test);
PG_FUNCTION_INFO_V1(tu64_cmp);

/*
 * Module load callback
 */
void
_PG_init(void)
{
	elog(DEBUG5, "pg_tu64:_PG_init():entry");

	if (!process_shared_preload_libraries_in_progress)
		return;

	elog(DEBUG5, "pg_tu64:_PG_init():exit");
}


/*
 *  Module unload callback
 */
void
_PG_fini(void)
{
}

Datum tu64_test(PG_FUNCTION_ARGS)
{
	uint64_t v1 = 32769;
	uint64_t v2 = 32768;
	PG_RETURN_BOOL ( v1 > v2 - (uint64_t)1 );
}

static int tu64_cmp_internal()
{
	uint64_t u1 = 32769;
	uint64_t u2 = 32768;
	uint64_t u3 = 1;
	uint64_t d;
	elog(LOG, "u1=%zu u2=%zu u3=%zu u2-u3=%zu u1>u2-u3=%d", u1, u2, u3, u2 - u3, u1 > (u2 - u3));
	d = u2 - u3;
	elog(LOG, "u1=%zu d=%zu u1>d=%d", u1, d, u1>d);
	return (u1 > d);
}

Datum tu64_cmp(PG_FUNCTION_ARGS)
{
	return tu64_cmp_internal();
}

