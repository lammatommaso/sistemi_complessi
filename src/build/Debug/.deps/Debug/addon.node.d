cmd_Debug/addon.node := ln -f "Debug/obj.target/addon.node" "Debug/addon.node" 2>/dev/null || (rm -rf "Debug/addon.node" && cp -af "Debug/obj.target/addon.node" "Debug/addon.node")
