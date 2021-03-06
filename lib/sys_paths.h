#ifndef _SYS_PATH_H
#define _SYS_PATH_H

// length the prefix takes up in the path
#define OBLI_PREFIX_LENGTH 9
#define OBLI_PREFIX_BASE ".oblip"

#define OBLID_PROCESS_NAME "oblid"

#define OBLI_DIR_PROFILES "profiles"
#define OBLI_DIR_MODULES "modules"
#define OBLI_DIR_NETWORK "network"
#define OBLI_DIR_PROGRAM "bin"
#define OBLI_DIR_LOG "log"
#define OBLI_DIR_TMP "tmp"

#define OBLI_FILE_DAEMON "dpidf"

int _obli_createFolderIfNotExists(const char *);

char *_obli_genPrefixPath(int, ...);
void _obli_freePrefixPath(char*);
void _obli_populatePrefix(int*);

#endif /* _SYS_PATH_H */