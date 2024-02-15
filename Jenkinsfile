@NonCPS
def buildVersionHistory() {
    def versionHistory = new Date().toString() + ",${env.JOB_NAME}_${env.BUILD_ID},"

    def changeLogSets = currentBuild.changeSets
    for (int i = 0; i < changeLogSets.size(); i++) {
        def entries = changeLogSets[i].items

        // Get Commit IDs
        for (int j = 0; j < entries.length; j++) {
            versionHistory += "${entries[j].commitId} "
        }

        versionHistory += ","

        // Get Commit Messages
        for (int j = 0; j < entries.length; j++) {
            versionHistory += "${entries[j].msg} "
        }

    }
    
    versionHistory += ", , "
    return versionHistory
}

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

                script {
                    def newVersionContent = buildVersionHistory().toString()
                    def versionHistoryLog = "${WORKSPACE}/VersionHistory.csv"

                    def previousVersionHistory = ""
                    if (fileExists(versionHistoryLog)) {
                        previousVersionHistory = readFile versionHistoryLog
                    } else {
                        previousVersionHistory = "Date,Build,Git Commit, Git Message"
                    }

                    writeFile   file: versionHistoryLog,
                                text: previousVersionHistory + "\n" + newVersionContent
                    archiveArtifacts artifacts: "VersionHistory.csv"
                }
            }
        }
    }
}