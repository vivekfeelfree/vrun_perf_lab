#!/usr/bin/env bash

# Systems Lab Orchestrator
# Usage: ./lab.sh [build|run|bench|clean] [module_number]

set -e

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

# Find all modules
get_modules() {
    ls -d [0-9][0-9]_* | sort
}

# Find a specific module by number
find_module() {
    local num=$1
    ls -d ${num}_* 2>/dev/null | head -n 1
}

build_module() {
    local mod_dir=$1
    echo -e "${BLUE}Building ${mod_dir}...${NC}"
    g++ -O3 -I./include "${mod_dir}/main.cpp" -o "${mod_dir}/experiment"
    echo -e "${GREEN}Build successful: ${mod_dir}/experiment${NC}"
}

run_module() {
    local mod_dir=$1
    if [ ! -f "${mod_dir}/experiment" ]; then
        build_module "$mod_dir"
    fi
    echo -e "${BLUE}Running ${mod_dir}...${NC}"
    "./${mod_dir}/experiment"
}

clean_module() {
    local mod_dir=$1
    rm -f "${mod_dir}/experiment"
    echo -e "Cleaned ${mod_dir}"
}

case "$1" in
    build)
        if [ -n "$2" ]; then
            build_module "$(find_module "$2")"
        else
            for m in $(get_modules); do build_module "$m"; done
        fi
        ;;
    run|bench)
        if [ -n "$2" ]; then
            run_module "$(find_module "$2")"
        else
            for m in $(get_modules); do run_module "$m"; done
        fi
        ;;
    clean)
        if [ -n "$2" ]; then
            clean_module "$(find_module "$2")"
        else
            for m in $(get_modules); do clean_module "$m"; done
        fi
        ;;
    all)
        for m in $(get_modules); do 
            build_module "$m"
            run_module "$m"
        done
        ;;
    *)
        echo "Usage: $0 {build|run|bench|clean|all} [module_number]"
        exit 1
        ;;
esac
