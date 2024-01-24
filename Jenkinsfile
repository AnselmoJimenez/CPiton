pipeline {
    agent any
    
    stages {
        stage('Build') {
            steps {
                sh './build.sh'
            }
        }
        stage('Test') {
            steps {
                sh 'echo "Testing help message"'
                sh './Piton -h'

                sh 'echo "Testing read.pi"'
                sh './Piton -f tests/read.pi'
            }
        }
        stage('Deploy') {
            steps {
                sh 'echo "DEPLOYING..."'
            }
        }
    }
}