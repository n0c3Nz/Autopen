#!/bin/bash

# --- CARGAR VALORES ESTATICOS ---
source ./estatico.sh

# --- CARGAR MODULOS ---
source $LOG

# --- VARIABLES GLOBALES ---
# --- FUNCTIONES AUXILIARES ---
function log_nmap {
    log_global "NMAP" "$1"
}

# --- INICIALIZACION ---

function test {
    log_nmap "test nmap"
}

