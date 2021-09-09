SRCDIR   := src
BUILDDIR := build
TARGET   := $(BUILDDIR)/Multiple_Choice_Quiz.AppImage

CXX      := g++
CXXFLAGS := -Wall -Wextra `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags webkit2gtk-4.0` -std=c++17
LDFLAGS  := `pkg-config --libs gtkmm-3.0` `pkg-config --libs webkit2gtk-4.0`

SRCS     := $(wildcard $(SRCDIR)/*.cpp)
OBJS     := $(addprefix $(BUILDDIR)/,$(SRCS:.cpp=.o))
DEPS     := $(OBJS:.o=.d)

.PHONY: all clean

all: clean $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(BUILDDIR)/$(SRCDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $< -o $@

clean:
	rm -rf $(BUILDDIR)

exec: $(TARGET)
	@$(TARGET)
