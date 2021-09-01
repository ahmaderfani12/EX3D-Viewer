#include"Material.h"
#include "SettingData.h"

Material::Material(ShaderType type,Shader* shader, Camera* camera)
{
	shaderType = type;
    this->shader = shader;
    this->camera = camera;
    
    glm::mat4 test(0.0f);
    test[0].w = 1.0;
    test[1].w = 1.0;
    test[2].w = 1.0;
    test[3].w = 1.0;
    objectModel = glm::translate(objectModel, objectPos);
    //objectModel = test * objectModel;
    shader->Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
}

void Material::UpdateShader()
{
    if (shaderType == ShaderType::normal) {
        UpdateNormal();
    }
    else if (shaderType == ShaderType::gizmo) {
        UpdateGizmo();
    }
}

void Material::UpdateNormal()
{
    //Fragment
    shader->Activate();
    glUniform4f(glGetUniformLocation(shader->ID, "lightColor"), SettingData::lightColor[0], SettingData::lightColor[1],
        SettingData::lightColor[2], 1.0f);

    glUniform4f(glGetUniformLocation(shader->ID, "ShadowColor"), SettingData::lightShadowColor[0], SettingData::lightShadowColor[1],
        SettingData::lightShadowColor[2], 1.0f);

    glUniform3f(glGetUniformLocation(shader->ID, "lightPos"), SettingData::lightPosition[0], SettingData::lightPosition[1],
        SettingData::lightPosition[2]);

    glUniform1f(glGetUniformLocation(shader->ID, "specularLight"), SettingData::specular);

    glUniform1f(glGetUniformLocation(shader->ID, "specularpower"), SettingData::specularPower);

    glUniform3f(glGetUniformLocation(shader->ID, "camPos"), camera->GetPosition().x, camera->GetPosition().y,
        camera->GetPosition().z);

    glUniform1f(glGetUniformLocation(shader->ID, "rimPower"), SettingData::rimPower);
    glUniform1f(glGetUniformLocation(shader->ID, "rimStrength"), SettingData::rimStrength);

    glUniform3f(glGetUniformLocation(shader->ID, "rimColor"), SettingData::rimColor[0], SettingData::rimColor[1],
        SettingData::rimColor[2]);


}

void Material::UpdateGizmo()
{

}
