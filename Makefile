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
	mkdir $(BUILDDIR)
	ln -s ../data/ ./$(BUILDDIR)/data

exec: $(TARGET)
	@$(TARGET)

out:
	mkdir $(BUILDDIR)/Multiple_Choice_Quiz
	cp $(BUILDDIR)/Multiple_Choice_Quiz.AppImage $(BUILDDIR)/Multiple_Choice_Quiz/
	cp -r data $(BUILDDIR)/Multiple_Choice_Quiz/
	tar cvf $(BUILDDIR)/Multiple_Choice_Quiz.tar.gz -C $(BUILDDIR) Multiple_Choice_Quiz
	rm -rf $(BUILDDIR)/Multiple_Choice_Quiz
