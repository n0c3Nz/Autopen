#!/bin/bash

function startLog {
    LOG_FILE="$LOG_DIR/$(date '+%Y%m%d_%H%M%S').log"
    touch $LOG_FILE
}

function log_global {
    if [ -n "$2" ]; then
        echo -e "[$1] $2" >> $LOG_FILE
    fi
}
