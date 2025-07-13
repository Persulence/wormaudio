FROM debian:trixie

RUN apt-get update && apt-get install -y openjdk-21-jdk

RUN mkdir /app
COPY build/libs/java_test-1.0-SNAPSHOT.jar /app
COPY src/main/resources/native/linux_amd64/libneepsound-java.so /app
COPY src/main/resources/native/linux_amd64/libneepsound.so /app
COPY test_system /app/test_system

WORKDIR /app/
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/jvm/java-21-openjdk-amd64/lib:.
RUN echo "oooooooo"
ENTRYPOINT ["java", "-jar", "java_test-1.0-SNAPSHOT.jar"]