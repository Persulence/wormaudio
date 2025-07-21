plugins {
    id("java")
//    id("application")
}

group = "com.wormaudio"
version = "1.0-SNAPSHOT"

java {
    toolchain {
        languageVersion = JavaLanguageVersion.of(17)
    }
}

repositories {
    mavenCentral()
}

dependencies {
    implementation("org.jetbrains:annotations:24.0.0")

//    implementation(platform("org.apache.logging.log4j:log4j-bom:2.25.1"))
//    implementation("org.apache.logging.log4j:log4j-api:2.6.1")
    implementation("org.slf4j:slf4j-api:2.0.17")
//    runtimeOnly("org.slf4j:slf4j-simple:2.0.17")

//    testImplementation(platform("org.junit:junit-bom:5.10.0"))
//    testImplementation("org.junit.jupiter:junit-jupiter")
}

//application {
//    applicationDefaultJvmArgs = arrayListOf("-Djava.library.path=" + file("${buildDir}/libs/hello/shared").absolutePath)
//}

//tasks.test {
//    useJUnitPlatform()
//}

tasks.jar {
    manifest {
        attributes(mapOf("Main-Class" to "com.wormaudio.WormAudioMain"))
    }
}