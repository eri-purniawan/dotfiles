#!/bin/bash

arch_update="$(checkupdates | wc -l)"
echo "$arch_update"
