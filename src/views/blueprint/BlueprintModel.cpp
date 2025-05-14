#include "../../../include/views/blueprint/BlueprintModel.h"

BlueprintModel::BlueprintModel(std::shared_ptr<Level> level) : m_level(level) {}

std::shared_ptr<Level> BlueprintModel::level() const {
    return m_level;
}

void BlueprintModel::setLevel(std::shared_ptr<Level> level) {
    if (m_level != level) {
        m_level = level;
    }
}
