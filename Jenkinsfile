pipeline {
    agent any
    
    stages {
        stage('Build') {
            steps {
                ./build.sh
            }
        }
        stage('Test') {
            steps {
                echo "Testing help message"
                ./Piton -h

                echo "Testing read.pi"
                ./Piton -f tests/read.pi
            }
        }
        stage('Deploy') {
            steps {
                sh 'echo "DEPLOYING..."'
            }
        }
    }
}