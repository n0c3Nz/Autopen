#!/bin/bash

export PROGRAM_DIR="$(dirname $0)"

# --- MODULOS ---
export MODULES_DIR="$PROGRAM_DIR/modulos"

#Descubrimiento
export MODULES_DESC="$MODULES_DIR/descubrimiento"
export NMAP="$MODULES_DESC/nmap/nmap.sh"

# --- MODULOS AUXILIARES ---
export MODULES_AUX_DIR="$PROGRAM_DIR/modulos_auxiliares"
export LOG="$MODULES_AUX_DIR/logs/log.sh"
export HELP="$MODULES_AUX_DIR/help/help.sh"

# --- LOGS ---
export LOG_DIR="$PROGRAM_DIR/log"
export LOG_FILE="$LOG_DIR/default.log"
