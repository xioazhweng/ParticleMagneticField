#include "ParamsPanel.h"


ParamsPanel::ParamsPanel (GLFWwindow * window): window_(window) {
   initPanel();
};

ParamsPanel::ParamsPanel(GLFWwindow * window, GLfloat width, GLfloat height, GLfloat offset): 
    window_(window), width_(width), height_(height), offset_(offset) {
    initPanel();
};

ParamsPanel::~ParamsPanel() {
    closePanel();
};
void ParamsPanel::initPanel() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
void ParamsPanel::render() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void ParamsPanel::drawPanel() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    int x = ImGui::GetIO().DisplaySize.x;
    int y = ImGui::GetIO().DisplaySize.y;
    ImGui::SetNextWindowPos(ImVec2(x - offset_, 0));
    ImGui::SetNextWindowSize(ImVec2(offset_, y*0.6));
    
    ImGui::Begin("System Parametrs");
    ImGui::InputDouble("q, e-19 C", &params.q_e19);
    ImGui::InputDouble("m, MeV/c²", &params.m_MeV);
    ImGui::InputDouble("Bx, Tl", &params.Bx);
    ImGui::InputDouble("Bz, Tl", &params.Bz);
    if (ImGui::IsKeyPressed(ImGuiKey_Space)) {
        paused_ = !paused_;
    }
    
    if (ImGui::Button("Pause"))  {
        paused_ = true; 
    } 
    if (ImGui::Button("Play")) {
        paused_ = false; 
    }
    if (ImGui::Button("Update"))
    {
        need_reset_ = true; 
    } else {
        need_reset_ = false; 
    }
    ImGui::SliderFloat("timescale", &params.timescale, 0, 4.0f);
    //ImGui::Text("Hello, world %d", 123);

    ImGui::PushItemWidth(-FLT_MIN);
    
    ImGui::InputFloat3("##r", params.r.data());
    ImGui::Text("r { x, y, z }");

    ImGui::InputFloat3("##v", params.v.data());
    ImGui::Text("v { vx, vy, vz }");

    ImGui::Text("Controls:");
    ImGui::Text("W / S  - Rotate camera up / down");
    ImGui::Text("A / D  - Rotate camera left / right");
    ImGui::Text("Q      - Zoom in");
    ImGui::Text("E      - Zoom out");
    ImGui::Text("SPACE  - Pause / Resume simulation");
    ImGui::Text("ESC    - Exit application");
    ImGui::End();
    ImGui::Render();
};

const SystemParams & ParamsPanel::getSystemParams() const {
    return params;
}

void ParamsPanel::closePanel() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}