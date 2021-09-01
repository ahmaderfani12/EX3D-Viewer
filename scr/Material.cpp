#include"Material.h"
#include "SettingData.h"

Material::Material(ShaderType type,Shader* shader, Camera* camera)
{
	shaderType = type;
    this->shader = shader;
    this->camera = camera;

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

    //Vertex
    glUniform3f(glGetUniformLocation(shader->ID, "worldPos"), SettingData::mainModelPos[0], SettingData::mainModelPos[1],
        SettingData::mainModelPos[2]);
    glUniform3f(glGetUniformLocation(shader->ID, "rotationAngle"), SettingData::mainModelAngle[0], SettingData::mainModelAngle[1],
        SettingData::mainModelAngle[2]);
    glUniform3f(glGetUniformLocation(shader->ID, "scale"), SettingData::mainModelScale[0], SettingData::mainModelScale[1],
        SettingData::mainModelScale[2]);

}

void Material::UpdateGizmo()
{

}
