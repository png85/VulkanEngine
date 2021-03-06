//
// Created by MTesseracT on 30-10-2017.
//

#ifndef VULKANENGINE_SIMPLERENDERER_HPP
#define VULKANENGINE_SIMPLERENDERER_HPP

#include <Core/MtVulkanAPI/VulkanRendererBase.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Core/MtVulkanAPI/VulkanModel.hpp>
#include <Core/Camera.hpp>

#include <vector>


class SimpleRenderer : public VulkanRendererBase
{
    VertexLayout m_vertexLayout = VertexLayout(
            {VulkanVertexComponent ::ePosition,
             VulkanVertexComponent ::eNormal,
             VulkanVertexComponent ::eUV,
             VulkanVertexComponent ::eColor}
    );

    const uint32_t VERTEX_BUFFER_BIND_ID = 0;

    struct {
        VulkanModel teapot;
    } m_models;

    struct UniformBufferObject {
        glm::mat4 projection;
        glm::mat4 modelView;
        glm::vec4 lightPos = glm::vec4(0.0f, 2.0f, 1.0f, 0.0f);
    } m_ubo;

    vk::Pipeline                m_phongPipeline;
    vk::PipelineLayout          m_pipelineLayout;
    vk::DescriptorSet           m_descriptorSet;
    vk::DescriptorSetLayout     m_descriptorSetLayout;

    WrappedVulkanBuffer         m_uniformBuffer;

    glm::vec3                   m_cameraPosition = glm::vec3();
    glm::vec3                   m_cameraRotation = glm::vec3(-25.0f, 15.0f, 0.0f);
    float                       m_cameraZoom     = -10.5f;

    //Camera*                     m_camera; //real camera

public:
    SimpleRenderer();

    ~SimpleRenderer() override;

    void Prepare() override;

    void GetEnabledFeatures() override;

    void Render() override;

    void BuildCommandBuffers() override;

    void LoadModels();

    void PrepareUniformBuffers();

    void UpdateUniformBuffers();

    void SetupDescriptorSetLayout();

    void PreparePipeline();

    void SetupDescriptorPool();

    void SetupDescriptorSet();
};


#endif //VULKANENGINE_SIMPLERENDERER_HPP
