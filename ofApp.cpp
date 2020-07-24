#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int R = 100;
	int u = 0;
	int u_step = 10;
	int v_step = 5;

	for (int i = 0; i < 36; i++) {

		float angle_z = (i * 5) * DEG_TO_RAD;
		auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

		auto noise_value = ofNoise(glm::vec3(cos(angle_z), sin(angle_z), ofGetFrameNum() * 0.01));
		int r = 15;
		if (noise_value > 0.55) {

			r = ofMap(noise_value, 0.55, 1, 15, 35);
		}

		for (auto v = 0; v < 360; v += v_step) {

			vector<glm::vec3> vertices{
				glm::vec4(this->make_point(R, r, u, v), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, u + u_step, v + v_step), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, u, v + v_step), 0) * rotation_z,
				glm::vec4(this->make_point(R, r, u - u_step, v), 0) * rotation_z
			};

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			auto index = this->face.getVertices().size() - 1;

			this->face.addIndex(index - 3); this->face.addIndex(index - 2); this->face.addIndex(index - 1);
			this->face.addIndex(index); this->face.addIndex(index - 3); this->face.addIndex(index - 1);

			this->frame.addIndex(index - 3); this->frame.addIndex(index - 2);
			this->frame.addIndex(index); this->frame.addIndex(index - 1);

			u += u_step;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(239);
	this->face.draw();

	ofSetColor(39);
	this->frame.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}