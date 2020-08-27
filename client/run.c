#include "run.h"

#include <obli.h>

#include <stdlib.h>
#include <stdint.h>
#include <colorprinter.h>

#include "constants.h"

const char *COMMANDS[] = {
    OBLI_CMD_HELP,
    OBLI_CMD_VERS,
    OBLI_CMD_START,
    OBLI_CMD_STARTW,
    OBLI_CMD_STARTS,
    OBLI_CMD_KILL,
    OBLI_CMD_INSTALL,
    OBLI_CMD_REMOVE,
    OBLI_CMD_LSMOD    
};

const char *COMMAND_BLURBS[] = {
    "Shows this help message",
    "Print current version string",
    "Alias for startWeak",
    "Start in weak mode with limited automation access",
    "Start in strong mode with full access to automation features",
    "Kill daemon and running obli instances",
    "Install module",
    "Remove module",
    "List all installed modules"
};

int _quickPrefix() {
    int prefixCreated = obli_setupPrefixIfNotExists();
    switch (prefixCreated) {
        case OBLI_FILESYS_ERROR:
            cfputs("Error creating prefix.", RED, stderr);
            break;

        case OBLI_PREFIX_CREATED:
            cputs("Created prefix.", GREEN);
            break;

        case OBLI_PREFIX_POPULATED:
            cputs("Populated prefix.", GREEN);
            break;

        case OBLI_PREFIX_OK:
        default:
            break; 
    }

    // returns Unix error codes but negative
    if (prefixCreated < 0)
        exit(prefixCreated * -1);
    
    return prefixCreated;
}

void runShowHelp(const char *programName) {
    printf("Usage: %s [option]. Please run \"%s help\" for help.\n\n", programName, programName);

    uint8_t numCommands = LEN_ARRAY(COMMANDS);
    for (int i = 0; i < numCommands; i++) {
        printf("\t\033[1m%s\033[0m: %s\n", COMMANDS[i], COMMAND_BLURBS[i]);
    }
}

void runStart(bool strong) {
    _quickPrefix();
    obli_launchDaemon();
}

void runEnd() {
    _quickPrefix();
    obli_killDaemon();
}

// assume num is the length of the array
void runInstall(int num, char **names) {
    _quickPrefix();

    for (int i = 0; i < num; i++) {
        const char *module = names[i];
        unsigned int hash = obli_hashModuleName(module);

        printf("%d. Install: %x (%s)... ", i+1, hash, module);
        obli_installModule(module);

        cputs("Done!", GREEN);
    }
}