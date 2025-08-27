#!/bin/bash

# --- BANNER ---
cat << 'EOF'
 ▄▄▄· ▄• ▄▌▄▄▄▄▄       ▄▄▄·▄▄▄ . ▐ ▄ 
▐█ ▀█ █▪██▌•██  ▪     ▐█ ▄█▀▄.▀·•█▌▐█
▄█▀▀█ █▌▐█▌ ▐█.▪ ▄█▀▄  ██▀·▐▀▀▪▄▐█▐▐▌
▐█ ▪▐▌▐█▄█▌ ▐█▌·▐█▌.▐▌▐█▪·•▐█▄▄▌██▐█▌
 ▀  ▀  ▀▀▀  ▀▀▀  ▀█▄▀▪.▀    ▀▀▀ ▀▀ █▪ Help
EOF

# --- CARGAR VALORES ESTATICOS ---
source ./estatico.sh
# --- CARGAR MODULOS ---
source $LOG
# --- VARIABLES GLOBALES ---
# --- FUNCIONES AUXILIARES ---
function log_help {
    log_global "HELP" "$1"
}
# --- FUNCIONES PRINCIPALES ---
function show_help {
    cat << 'EOF'
==============================================

DESCRIPCIÓN:
 Herramienta de automatización para pruebas de penetración
 que permite ejecutar diferentes módulos de descubrimiento
 y análisis de seguridad de forma organizada.

USO:
 ./main.sh [OPCIONES]

OPCIONES:
 --help, -h Muestra esta información de ayuda

MÓDULOS DISPONIBLES:
 • Descubrimiento:
 - NMAP: Escaneo de puertos y servicios

 • Auxiliares:
 - LOG: Sistema de registro de actividades
 - HELP: Sistema de ayuda (este módulo)

ESTRUCTURA DE DIRECTORIOS:
 modulos/ - Módulos principales de pentesting
 modulos_auxiliares/ - Módulos auxiliares y utilidades
 log/ - Archivos de registro

EJEMPLOS:
 ./main.sh # Ejecuta la herramienta normalmente
 ./main.sh --help # Muestra esta ayuda
 ./main.sh -h # Muestra esta ayuda

==============================================
EOF

    log_help "Información de ayuda mostrada"
}

# --- LÓGICA PRINCIPAL ---
if [[ "$1" == "--help" || "$1" == "-h" ]]; then
    show_help
    exit 0
fi

# Resto de la lógica de tu script aquí...
