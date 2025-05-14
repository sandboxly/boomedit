#ifndef BLUEPRINTMODEL_H
#define BLUEPRINTMODEL_H

#include "../../models/Level.h"

class BlueprintModel
{
public:
    explicit BlueprintModel(std::shared_ptr<Level> level);

    std::shared_ptr<Level> level() const;
    void setLevel(std::shared_ptr<Level> level);
private:
    std::shared_ptr<Level> m_level;
};

#endif // BLUEPRINTMODEL_H
