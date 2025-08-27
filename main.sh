#!/bin/bash

# --- CARGAR VALORES ESTATICOS ---
source ./estatico.sh

# --- CARGAR MODULOS ---
source $NMAP
source $LOG
source $HELP

# --- MANEJO DE ARGUMENTOS ---
if [[ "$1" == "--help" || "$1" == "-h" ]]; then
    show_help
    exit 0
fi

# --- VARIABLES GLOBALES ---
# --- FUNCTIONES AUXILIARES ---
function log_main {
    log_global "MAIN" "$1"
}

# --- INICIALIZACION ---
startLog
log_main "test"

test

log_main "hola"
