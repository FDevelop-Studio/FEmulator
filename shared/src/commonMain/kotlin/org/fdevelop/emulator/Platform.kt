package com.fdevelop.emulator

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform