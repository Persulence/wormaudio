plugins {
    id("java")
//    id("application")
}

group = "com.neep"
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
//    implementation(files("NEEPSound.jar"))
//    testImplementation(platform("org.junit:junit-bom:5.10.0"))
//    testImplementation("org.junit.jupiter:junit-jupiter")
}

//application {
//    applicationDefaultJvmArgs = arrayListOf("-Djava.library.path=" + file("${buildDir}/libs/hello/shared").absolutePath)
//}

//tasks.test {
//    useJUnitPlatform()
//}