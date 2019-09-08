#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 180;
	int len = 150;
	for (int x = span * 0.5; x < ofGetWidth(); x += span) {

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			vector<glm::vec2> right, left;
			for (auto param = 0; param <= 50; param++) {

				auto noise_value = ofNoise(x, y, param * 0.08, ofGetFrameNum() * 0.01);

				if (noise_value < 0.65) {

					right.push_back(this->make_point(len, param) + glm::vec2(x, y));
					left.push_back(this->make_point(len, 100 - param) + glm::vec2(x, y));
				}
				else {

					this->draw_shape(right, left);
				}
			}

			this->draw_shape(right, left);
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
void ofApp::draw_shape(vector<glm::vec2>& param_1, vector<glm::vec2>& param_2) {

	if (param_1.size() > 0 && param_2.size() > 0) {

		std::reverse(param_2.begin(), param_2.end());

		ofColor color;
		color.setHsb(((int)(param_1[0].x + param_1[0].y + 255) % 255), 180, 255);

		ofFill();
		ofSetColor(color, 200);
		
		ofBeginShape();
		ofVertices(param_1);
		ofVertices(param_2);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		ofVertices(param_1);
		ofVertices(param_2);
		ofEndShape(true);

		param_1.clear();
		param_2.clear();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}