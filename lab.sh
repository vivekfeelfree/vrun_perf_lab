#!/usr/bin/env bash

# Systems Lab Orchestrator v2.0
# Usage: ./lab.sh [build|run|bench|clean|all] [module_number]

set -e
set -o pipefail

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

LOG_DIR="logs"
mkdir -p "$LOG_DIR"

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
    
    local mod_name=$(basename "$mod_dir")
    local log_file="$LOG_DIR/${mod_name}.log"
    
    echo "=== Module: $mod_name ===" > "$log_file"
    local start_time=$(date +%s%3N)
    local start_human=$(date "+%Y-%m-%d %H:%M:%S.%3N")
    echo "Start Time: $start_human" >> "$log_file"
    echo "------------------------------------------" >> "$log_file"
    
    echo -e "${BLUE}Running ${mod_dir}...${NC}"
    
    # Strict 2-minute timeout
    set +e
    timeout 120s "./${mod_dir}/experiment" 2>&1 | tee -a "$log_file"
    local status=$?
    set -e

    local end_time=$(date +%s%3N)
    local end_human=$(date "+%Y-%m-%d %H:%M:%S.%3N")
    local total_ms=$((end_time - start_time))
    
    echo "------------------------------------------" >> "$log_file"
    echo "End Time: $end_human" >> "$log_file"
    echo "Total Execution Time: ${total_ms}ms" >> "$log_file"

    if [ $status -eq 124 ]; then
        echo -e "${RED}[TIMEOUT] ${mod_dir} exceeded 2 minute limit.${NC}"
        echo "Status: TIMEOUT" >> "$log_file"
    elif [ $status -ne 0 ]; then
        echo -e "${RED}[ERROR] ${mod_dir} failed with exit code $status.${NC}"
        echo "Status: ERROR ($status)" >> "$log_file"
    else
        echo -e "${GREEN}[SUCCESS] ${mod_dir} completed in ${total_ms}ms.${NC}"
        echo "Status: SUCCESS" >> "$log_file"
    fi
    
    # Also append to global run.log for summary
    echo "[$(date "+%H:%M:%S")] $mod_name | Status: $status | Time: ${total_ms}ms" >> run.log
}

clean_module() {
    local mod_dir=$1
    rm -f "${mod_dir}/experiment"
    echo -e "${BLUE}Cleaned ${mod_dir}${NC}"
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
        echo "=== Lab Summary: $(date) ===" > run.log
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
        echo "=== Lab Summary: $(date) ===" > run.log
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
