#!/bin/bash
 
 for i in $(seq 1 $1 )
     do $2 "${@:3}"
 done