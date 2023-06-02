#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	float span = 3;
	ofColor color;

	for (float x = 30; x < ofGetWindowWidth() - 30 - span; x += span) {

		for (float y = 30; y < ofGetWindowHeight() - 30 - span; y += span) {

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
			this->mesh.addVertex(glm::vec3(x, y + span, 0));

			for (int i = this->mesh.getNumVertices() - 4; i < this->mesh.getNumVertices(); i++) {

				auto noise_value = ofMap(ofNoise(this->mesh.getVertex(i).x * 0.005, this->mesh.getVertex(i).y * 0.005, ofGetFrameNum() * 0.015), 0, 1, 0, 2);
				int int_noise_value = noise_value;
				float param = noise_value - int_noise_value;
				param = abs(param - 0.5);

				color.setHsb(ofMap(int_noise_value, 0, 2, 0, 255), 255, 255, param < 0.35 ? ofMap(param, 0, 0.35, 255, 0) : 0);
				this->mesh.addColor(color);
			}

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}